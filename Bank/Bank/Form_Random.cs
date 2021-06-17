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
    public partial class Form_Random : Form
    {
        public Form_Random()
        {
            InitializeComponent();
        }

        public int GetCount() // метод для отсылки значения
        {
            int a;
            int.TryParse(maskedTextBox1.Text, out a);
            return a;
        }

        private void button1_Click(object sender, EventArgs e) // кнопка Создать
        {
            int a;
            int.TryParse(maskedTextBox1.Text, out a);
            if (maskedTextBox1.Text == "") MessageBox.Show("Введите кол-во элементов!");
            else if (a == 0) { MessageBox.Show("Введите ненулевое значение!"); maskedTextBox1.Clear(); }
            else this.Close();
        }

        private void button2_Click(object sender, EventArgs e) // кнопка Отмена
        {
            this.Close();
        }
    }
}
