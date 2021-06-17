using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bank
{
    [Serializable]
    abstract public class Client
    {
        private int id;
        private string name;
        private string surname;
        private string birth;
        private string passport;

        private List<string> credit = new List<string>();  
        private List<string> deposit = new List<string>(); 

       
        // СВОЙСТВА
        #region
        public int ID
        {
            get
            {
                id = this.GetHashCode();
                return id;
            }
            protected set { ID = value; }
        }
        public string Name 
        {
            get { return name; }
            set
            {
                name = value.Trim();
            }
        }
        public string Surname
        {
            get { return surname; }
            set
            {
                surname = value.Trim();
            }
        }
        public string Passport
        {
            get { return passport; }
            set
            {
                value = value.Trim();
                if(value.Length == 10) passport = value;
            }
        }
        public string Birth
        {
            get { return birth; }
            set
            {
                DateTime parsedDate;
                try
                {
                    parsedDate = DateTime.Parse(value);
                }
                catch
                {
                    birth = "нет данных"; return;
                }
                birth = value;
            }
        }
        public List<string> Credit
        {
            get { return credit; }
            set { credit = value; }
        }
        public List<string> Deposit
        {
            get { return deposit; }
            set { deposit = value; }
        }
        #endregion
        // КОНСТРУКТОРЫ
        #region
        public Client() 
        {
            name = "Имя";
            surname = "Фамилия";
            birth = "нет данных";
            passport = "нет данных";
        }
        public Client(string n, string s, string b, string pas)
        {
            name = n;
            surname = s;
            birth = b;
            passport = pas;
        }
        #endregion
        // МЕТОДЫ
        public int CreditLength
        {
            get { return credit.Count; }
        }
        public int DepositLength
        {
            get { return deposit.Count; }
        }
        public void NewCredit(string sum, string period, string rate) 
        {
            string str = $"Кредит - {sum} по ставке {rate}, период: {period} года/лет";
            credit.Add(str);
        }
        public void NewDeposit(string sum, string period, string rate)
        {
            string str = $"Вклад - {sum} по ставке {rate}, период: {period} года/лет";
            deposit.Add(str);
        }

        public abstract override string ToString();
        public abstract override int GetHashCode();
        public abstract override bool Equals(object obj);
    }
}
