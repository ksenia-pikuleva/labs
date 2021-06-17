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
    public partial class Form_NewClient : Form
    {
        List<Client> clientlist = new List<Client>();
        string[] mas = { "Физическое лицо", "Юридическое лицо" };
        public Form_NewClient()
        {
            InitializeComponent();
            comboBox1.DataSource = mas;
        }

        public List<Client> GetClient()
        {
            return clientlist;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e) 
        {
            if (comboBox1.SelectedIndex == 0) // физ лицо
            {
                panel1.Visible = true;
                panel1.Enabled = true;
                panel2.Visible = false;
                panel2.Enabled = false;
            }
            if (comboBox1.SelectedIndex == 1) // юр лицо
            {
                panel2.Visible = true;
                panel2.Enabled = true;
                panel1.Visible = false;
                panel1.Enabled = false;
            }
        }
        private void button2_Click(object sender, EventArgs e) // кнопка Отмена
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e) // кнопка Добавить клиента
        {
            if(textBox2.Text !="" && textBox3.Text != "" && maskedTextBox2.Text != "" && maskedTextBox3.Text != "")
            {
                if (comboBox1.SelectedValue.ToString() == "Физическое лицо") // заполняем
                {
                    clientlist.Add(new Client_Individual());
                    clientlist[0].Name = textBox2.Text;
                    clientlist[0].Surname = textBox3.Text;
                    clientlist[0].Birth = maskedTextBox2.Text;
                    clientlist[0].Passport = maskedTextBox3.Text;
                    (clientlist[0] as Client_Individual).Phone = maskedTextBox1.Text;
                }
                if (comboBox1.SelectedValue.ToString() == "Юридическое лицо")
                {
                    clientlist.Add(new Client_LegalEntity());
                    clientlist[0].Name = textBox2.Text;
                    clientlist[0].Surname = textBox3.Text;
                    clientlist[0].Birth = maskedTextBox2.Text;
                    clientlist[0].Passport = maskedTextBox3.Text;
                    (clientlist[0] as Client_LegalEntity).Company = textBox1.Text;
                }
                this.Close();
            }
            else
            {
                MessageBox.Show("Заполните все обязательные поля!");
                return;
            }            
            
        }
    }
}
