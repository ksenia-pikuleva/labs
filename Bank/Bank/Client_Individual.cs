using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bank
{
    [Serializable]
    public class Client_Individual : Client
    {
        private string phone;
        static Random rnd = new System.Random(); 

        // СВОЙСТВА
        public string Phone
        {
            get { return phone; }
            set
            {
                if(value[0]=='+' && value[1]=='7' && value.Length==12) phone = value; 
            }
        }

        // КОНСТРУКТОРЫ
        public Client_Individual() : base()
        {
            phone = "нет данных";
        }
        public Client_Individual(string n, string s, string b, string pas, string ph) : base(n, s, b, pas)
        {
            phone = ph;
        }

        // МЕТОДЫ
        public override string ToString()
        {
            return $"{Name} {Surname} | ДР {Birth} | Пасспорт {Passport} | Телефон {Phone}";
        }

        public override int GetHashCode()
        {
            return Math.Abs(Name.GetHashCode() + Surname.GetHashCode() + Passport.GetHashCode() + Birth.GetHashCode() + Phone.GetHashCode()) % 100000;
        }

        public override bool Equals(object obj)
        {
            if (null == obj)//Если obj не инициализирован
                return false;
            if ((obj is Client_Individual) == false) //Если невозможно привести obj к соотв типу
                return false;
            Client_Individual x = (Client_Individual)obj;
            return Name == x.Name && Surname == x.Surname && Passport == x.Passport && Birth == x.Birth && Phone == x.Phone;
        }

        public Client_Individual Random()
        {
            string[] NamesM = { "Олег", "Дмитрий", "Владимир", "Сергей", "Андрей", "Павел", "Денис", "Семен", "Виталий", "Егор", "Алексей", "Тимофей", "Игорь", "Константин"};
            string[] NamesW = { "Анна", "Екатерина", "Татьяна", "Елена", "Мария", "Светлана", "Елизавета", "Анастасия", "Юлия", "Ирина", "Софья", "Виктория", "Алиса", "Любовь"};
            string[] SurnamesM = { "Иванов", "Петров", "Шишкин", "Масленников", "Овечкин", "Попов", "Соловьев", "Киселев", "Федоров", "Дорофеев", "Гончаров", "Новиков", "Морозов", "Петухов" };
            string[] SurnamesW = { "Иванова", "Петрова", "Шишкина", "Масленникова", "Овечкина", "Попова", "Соловьева", "Киселева", "Федорова", "Дорофеева", "Гончарова", "Новикова", "Морозова", "Петухова" };

            Client_Individual client = new Client_Individual();
            int a = rnd.Next();
            if(a%2 == 0) // фамилия имя
            {
                client.Name = NamesM[rnd.Next(14)];
                client.Surname = SurnamesM[rnd.Next(14)];
            }
            else
            {
                client.Name = NamesW[rnd.Next(14)];
                client.Surname = SurnamesW[rnd.Next(14)];
            }

            string passtr = ""; // паспорт телефон
            string phonestr = "+7";
            for (int i=0; i<10; i++)
            {
                a = rnd.Next(10);
                passtr += a.ToString();
                a = rnd.Next(10);
                phonestr += a.ToString();
            }
            client.Passport = passtr;
            client.Phone = phonestr;

            DateTime from = new DateTime(1970, 1, 1, 0, 0, 0); // дата рождения
            DateTime to = new DateTime(2000, 1, 1, 0, 0, 0);
            DateTime birthday = GenRandomDateTime(from, to, rnd);
            client.Birth = birthday.ToShortDateString();

            return client;
        }

        static DateTime GenRandomDateTime(DateTime from, DateTime to, Random random = null) 
        {
            if (random == null)
            {
                random = new Random();
            }
            TimeSpan range = to - from;
            var randts = new TimeSpan((long)(random.NextDouble() * range.Ticks));
            return from + randts;
        }
    }
}
