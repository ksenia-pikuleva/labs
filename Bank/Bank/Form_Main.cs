using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;


namespace Bank
{

    public partial class Form_Main : Form
    {
        // ПОЛЯ
        MyClientList_events Bank = new MyClientList_events("Сбербанк"); // коллекция с событиями
        Journal Journal = new Journal();                                        // список событий
        Random rnd = new Random();
        int CountOfClients = 0;                                                 // кол-во клиентов для рандома

        // КОНСТРУКТОР
        public Form_Main()
        {
            InitializeComponent();
            Bank.ChangingEvent += new CollectionHandler(Journal.SomeEvent); // Производим подписку на событие - добавлене обработчика событий
        }

        // МЕТОДЫ
        private void SuperUpdate() // метод для обновления таблицы по коллекции
        {
            if (Bank.Count != 0)
            {
                this.DBView.RowCount = Bank.Count;
                for (int i = 0; i < Bank.Count; i++)
                {
                    this.DBView.Rows[i].Cells[0].Value = Bank[i].ID;
                    this.DBView.Rows[i].Cells[1].Value = Bank[i].Surname + " " + Bank[i].Name;
                    this.DBView.Rows[i].Cells[2].Value = Bank[i].Passport;
                    this.DBView.Rows[i].Cells[3].Value = Bank[i].Birth;
                    if (Bank[i] is Client_Individual) this.DBView.Rows[i].Cells[4].Value = "Физ лицо";
                    if (Bank[i] is Client_LegalEntity) this.DBView.Rows[i].Cells[4].Value = "Юр лицо";
                }

            } 
            else
            {
                DBView.Rows.Clear();
                очиститьСписокToolStripMenuItem.Enabled = false;
                удалитьКлиентаToolStripMenuItem.Enabled = false;
                return;
            }         
        }
        private void автозаполнениеToolStripMenuItem_Click(object sender, EventArgs e) // кнопка Автозаполнение
        {
            Form_Random FR = new Form_Random();
            FR.ShowDialog();
            CountOfClients = FR.GetCount();
            for (int i=0; i<CountOfClients; i++)
            {
                // создаем объекты и добавляем их в список клиентов
                Bank.AddClient(new Client_Individual().Random());
                Bank.AddClient(new Client_LegalEntity().Random());
            }
            // сортировка по ID или хз что это
            var TempCollection = from x in Bank orderby x.ID select x;

            int l = 0;
            foreach (Client x in TempCollection)
            {
                Bank[l++] = x;
            }
            SuperUpdate();
            удалитьКлиентаToolStripMenuItem.Enabled = true;
            очиститьСписокToolStripMenuItem.Enabled = true;
        }

        private void KeySearch(object sender, EventArgs e) // ПОИСК изменить для вывода найденных строк
        {
            if (textBox1.Text != "")
            { 
                for (int i = 0; i < DBView.RowCount; i++)
                {
                    DBView.Rows[i].Selected = false;
                    for (int j = 0; j < DBView.ColumnCount; j++)
                        if (DBView.Rows[i].Cells[j].Value != null)
                            if (DBView.Rows[i].Cells[j].Value.ToString().Contains(textBox1.Text))
                            {
                                DBView.Rows[i].Selected = true;
                                break;
                            }
                }
                Journal.OtherEvent(Bank.BankBranchName, "Поиск выполнен!");
            }
            else
            {
                for (int i = 0; i < DBView.RowCount; i++)
                {
                    DBView.Rows[i].Selected = false;
                }
            }
        }

        private void Form_Main_Load(object sender, EventArgs e) // загрузка формы
        {
            textBox1.Enabled = false;

            удалитьКлиентаToolStripMenuItem.Enabled = false;
            очиститьСписокToolStripMenuItem.Enabled = false;
            Journal.OtherEvent(Bank.BankBranchName, "Запуск приложения"); // супер запись для других событий
        }

        private void button2_Click(object sender, EventArgs e) // кнопка Кредит
        {
            DataGridViewSelectedCellCollection selectedCells = DBView.SelectedCells; // выделенные записи
            if (Bank.Length == 0) // пустая таблица
            {
                MessageBox.Show("Таблица пуста! Заполните таблицу!.",
                             "Oops!", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                return;
            }
            if (selectedCells.Count == 0) // элемент не выделен
            {
                MessageBox.Show("Требуются выдерленные элементы. Выделете один (ЛКМ по элементу).",
                           "Oops!", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                return;
            }

            Client client = Bank[selectedCells[0].RowIndex];
            Form_Credit FC = new Form_Credit(client);
            FC.ShowDialog();
            string rate = "10,9 %";
            if (FC.GetSum() != "" && FC.GetPeriod() != "")
            {
                Bank.AddCredit(client, FC.GetSum(), FC.GetPeriod(), rate);
                MessageBox.Show("Кредит оформлен!");
            }
            
        }

        private void button3_Click(object sender, EventArgs e) // кнопка Вклад
        {
            DataGridViewSelectedCellCollection selectedCells = DBView.SelectedCells; // выделенные записи
            if (Bank.Length == 0)
            {
                MessageBox.Show("Таблица пуста! Заполните таблицу!.",
                             "Oops!", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                return;
            }
            if (selectedCells.Count == 0)
            {
                MessageBox.Show("Требуются выдерленные элементы. Выделете один (ЛКМ по элементу), либо несколько элементов (CTRL+ЛКМ).",
                           "Oops!", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                return;
            }

            Client client = Bank[selectedCells[0].RowIndex];
            Form_Deposit FD = new Form_Deposit(client);
            FD.ShowDialog();
            string rate = "5,89 %";
            if (FD.GetSum() != "" && FD.GetPeriod() != "")
            {
                Bank.AddDeposit(client, FD.GetSum(), FD.GetPeriod(), rate);
                MessageBox.Show("Вклад открыт!");
            }
        }

        private void добавитьКлиентаToolStripMenuItem_Click(object sender, EventArgs e) // кнопка Добавить клиента
        {
            List<Client> obj = new List<Client>();
            Form_NewClient FN = new Form_NewClient();
            FN.ShowDialog();
            obj = FN.GetClient(); // если он пуст, значит ничего не произошло
            if(obj.Count != 0)
            {
                Bank.AddClient(obj[0]);
                SuperUpdate();
                MessageBox.Show($"Клиент {obj[0].ID} добавлен!");
                удалитьКлиентаToolStripMenuItem.Enabled = true;
                textBox1.Enabled = true;
            }            
        }

        private void удалитьКлиентаToolStripMenuItem_Click(object sender, EventArgs e) // кнопка Удалить клиента
        {
            DataGridViewSelectedCellCollection selectedCells = DBView.SelectedCells; // выделенная запись
            if (selectedCells.Count != 0)
            {
                Client client = Bank[selectedCells[0].RowIndex];
                Bank.RemoveClient(client);
                SuperUpdate();
                MessageBox.Show($"Клиент {client.ID} удален из списка клиентов!");
            }
            else
            {
                MessageBox.Show("Требуются выдерленные элементы. Выделете один (ЛКМ по элементу).",
                          "Oops!", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                return;
            }
        }

        private void открытьToolStripMenuItem1_Click(object sender, EventArgs e) // кнопка Сохранить список клиентов
        {
            saveFileDialog1.Filter = "Bank files |*.bnk";
            if (saveFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                BinaryFormatter formatter = new BinaryFormatter();
                using (Stream fs = saveFileDialog1.OpenFile())
                {
                    formatter.Serialize(fs, Bank);
                }
            }
            Journal.OtherEvent(Bank.BankBranchName, "Текущий список клиентов сохранен в файл!");
        }

        private void открытьToolStripMenuItem_Click(object sender, EventArgs e) // кнопка Открыть список клиентов
        {
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                string ext = Path.GetExtension(openFileDialog1.FileName); // Получаем расширение выбранного файла.
                if (ext == ".bnk")
                {
                    try
                    {
                        BinaryFormatter formatter = new BinaryFormatter();
                        using (Stream fs = openFileDialog1.OpenFile())
                        {
                            Bank = (MyClientList_events)formatter.Deserialize(fs);
                        }
                        SuperUpdate();
                        Journal.OtherEvent(Bank.BankBranchName, "Список клиентов открыт из файла!");
                        textBox1.Enabled = true;
                    }
                    catch (Exception)
                    {
                        MessageBox.Show("Ошибка чтения, вероятно файл поврежден.",
         "Oops!", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                    }
                }
                else MessageBox.Show("Неверное расширение файла. Требуемое расширение \".bnk\"",
                         "Oops!", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
            }
            удалитьКлиентаToolStripMenuItem.Enabled = true;
        }
        
        private void UpdateJournal(object sender, EventArgs e) // обновление Журнала на вкладке при SelectedIndexChanged
        {
            richTextBox1.Clear();
            //  из текстового файла
            //richTextBox1.Text = File.ReadAllText(@"D:\Рабочий стол\Bank\txt__12.01.2020.txt", Encoding.Default);

            // из списка Journal
            foreach (JournalEntry Entry in Journal)
            {
                richTextBox1.Text += $" {Entry.ToString()} \n";
            }
        }

        private void очиститьСписокToolStripMenuItem_Click(object sender, EventArgs e) // кнопка Очистить список
        {
            if (Bank.Length != 0)
            {
                Bank.ClearList();
                Journal.OtherEvent(Bank.BankBranchName, "Список клиентов очищен!");
                SuperUpdate();
                MessageBox.Show("Список клиентов очищен!");
            }
            else MessageBox.Show("Список пуст! Заполните таблицу!.",
                             "Oops!", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
        }

        private void button1_Click(object sender, EventArgs e) // кнопка Открыть Журнал из Архива НЕ РАБОТАЕТ
        {
            string text;
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                string ext = Path.GetExtension(openFileDialog1.FileName); // Получаем расширение выбранного файла.
                if (ext == ".txt")
                {
                    try
                    {
                        BinaryFormatter formatter = new BinaryFormatter();
                        using (Stream fs = openFileDialog1.OpenFile())
                        {
                            StreamReader sr = new StreamReader(fs, Encoding.GetEncoding(1251));
                            text = sr.ReadToEnd();
                            richTextBox1.Text = text;
                            richTextBox1.ScrollToCaret();
                        }
                    }
                    catch (Exception)
                    {
                        MessageBox.Show("Ошибка чтения, вероятно файл поврежден.",
         "Oops!", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                    }
                }
                else MessageBox.Show("Неверное расширение файла. Требуемое расширение \".bnk\"",
                         "Oops!", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
            }
        }

        private void ScrollToEnd(object sender, EventArgs e)
        {
            richTextBox1.SelectionStart = richTextBox1.Text.Length;
            richTextBox1.ScrollToCaret();
        }

    }
}
