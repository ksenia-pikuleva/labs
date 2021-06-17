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

    public partial class Form_Credit : Form
    {
        string sum = "";
        string period = "";

        public Form_Credit()
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

        public Form_Credit(Client client) // специальный конструктор
        {
            InitializeComponent();
            label1.Text += client.ID;
            if (client is Client_Individual)
            {
                listBox1.Items.Add("Физическое лицо");
                listBox1.Items.Add($"{client.Name} {client.Surname}");
                listBox1.Items.Add($"Дата рождения: {client.Birth}");
                listBox1.Items.Add($"Паспорт: {client.Passport}");
                listBox1.Items.Add($"Телефон: {(client as Client_Individual).Phone}");
                if (client.CreditLength !=0 )
                {
                    listBox1.Items.Add($"Текущие Кредиты:");
                    for(int i=0; i<client.CreditLength; i++) // длина списка кредитов
                    {
                        listBox1.Items.Add(client.Credit[i]); // доступ к каждому элементу списка
                    }
                }
            }

            if (client is Client_LegalEntity)
            {
                listBox1.Items.Add("Юридическое лицо");
                listBox1.Items.Add($"{client.Name} {client.Surname}");
                listBox1.Items.Add($"Дата рождения: {client.Birth}");
                listBox1.Items.Add($"Паспорт: {client.Passport}");
                listBox1.Items.Add($"Компания: {(client as Client_LegalEntity).Company}");
                if (client.CreditLength != 0)
                {
                    listBox1.Items.Add($"Текущие Кредиты:");
                    for (int i = 0; i < client.CreditLength; i++) // длина списка кредитов
                    {
                        listBox1.Items.Add(client.Credit[i]); // доступ к каждому элементу списка
                    }
                }
            }
            textBox1.Text = "10,9 %";
        }

        private void button1_Click(object sender, EventArgs e) // кнопка Оформить кредит
        {
            if(maskedTextBox1.Text !="" && maskedTextBox2.Text != "")
            {
                sum = maskedTextBox1.Text;
                period = maskedTextBox2.Text;
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
