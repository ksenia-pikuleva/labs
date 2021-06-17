using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Bank
{

    public partial class Form_Deposit : Form
    {
        string[] mas = { "90", "180", "380", "1830", "бессрочный" };
        string sum = "";
        string period = "";
        public Form_Deposit()
        {
            InitializeComponent();
        }

        public string GetSum()
        {
            return sum;
        }
        public string GetPeriod()
        {
            return period;
        }

        public Form_Deposit(Client client) // специальный конструктор
        {
            InitializeComponent();
            label1.Text += client.ID;
            if (client is Client_Individual)
            {
                listBox1.Items.Add($"{client.Name} {client.Surname}");
                listBox1.Items.Add($"Дата рождения: {client.Birth}");
                listBox1.Items.Add($"Паспорт: {client.Passport}");
                listBox1.Items.Add($"Телефон: {(client as Client_Individual).Phone}");
                if (client.DepositLength != 0)
                {
                    listBox1.Items.Add($"Текущие Вклады:");
                    for (int i = 0; i < client.DepositLength; i++) // длина списка кредитов
                    {
                        listBox1.Items.Add(client.Deposit[i]); // доступ к каждому элементу списка
                    }
                }
            }

            if (client is Client_LegalEntity)
            {
                listBox1.Items.Add($"{client.Name} {client.Surname}");
                listBox1.Items.Add($"Дата рождения: {client.Birth}");
                listBox1.Items.Add($"Паспорт: {client.Passport}");
                listBox1.Items.Add($"Компания: {(client as Client_LegalEntity).Company}");
                if (client.DepositLength != 0)
                {
                    listBox1.Items.Add($"Текущие Вклады:");
                    for (int i = 0; i < client.DepositLength; i++) // длина списка кредитов
                    {
                        listBox1.Items.Add(client.Deposit[i]); // доступ к каждому элементу списка
                    }
                }
            }
            textBox1.Text = "5,89 %";
            comboBox1.DataSource = mas;
        }

        private void button1_Click(object sender, EventArgs e) // кнопка Открыть вклад
        {
            if (maskedTextBox1.Text != "" && comboBox1.SelectedValue != null)
            {
                sum = maskedTextBox1.Text;
                period = comboBox1.SelectedValue.ToString();
                this.Close();
            }
            else
            {
                MessageBox.Show("Введите все необходимые данные!");
                return;
            }
        }
    }
}
