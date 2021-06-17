using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bank
{
    [Serializable]
    public class Client_LegalEntity : Client
    {
        private string company;
        static Random rnd = new System.Random(); 

        // СВОЙСТВА
        public string Company
        {
            get { return company; }
            set { company = value; }
        }

        // КОНСТРУКТОРЫ
        public Client_LegalEntity() : base()
        {
            company = "нет данных";
        }
        public Client_LegalEntity(string n, string s, string b, string pas, string c) : base(n, s, b, pas)
        {
            company = c;
        }
        // МЕТОДЫ
        public override string ToString()
        {
            return $"{Name} {Surname} | ДР {Birth} | Пасспорт {Passport} | Компания '{Company}'";
        }

        public override int GetHashCode()
        {
            return Math.Abs(Name.GetHashCode() + Surname.GetHashCode() + Passport.GetHashCode() + Birth.GetHashCode() + Company.GetHashCode()) % 100000;
        }

        public override bool Equals(object obj)
        {
            if (null == obj)//Если obj не инициализирован
                return false;
            if ((obj is Client_LegalEntity) == false) //Если невозможно привести obj к соотв типу
                return false;
            Client_LegalEntity x = (Client_LegalEntity)obj;
            return Name == x.Name && Surname == x.Surname && Passport == x.Passport && Birth == x.Birth && Company == x.Company;
        }

        public Client_LegalEntity Random()
        {
            
            string[] Companies = { "ООО Цветник", "ИП Кондитер", "ОАО Автостарт" };
            string[] NamesM = { "Олег", "Дмитрий", "Владимир", "Сергей", "Андрей", "Павел", "Денис", "Семен", "Виталий", "Егор", "Алексей", "Тимофей", "Игорь", "Константин" };
            string[] NamesW = { "Анна", "Екатерина", "Татьяна", "Елена", "Мария", "Светлана", "Елизавета", "Анастасия", "Юлия", "Ирина", "Софья", "Виктория", "Алиса", "Любовь" };
            string[] SurnamesM = { "Иванов", "Петров", "Шишкин", "Масленников", "Овечкин", "Попов", "Соловьев", "Киселев", "Федоров", "Дорофеев", "Гончаров", "Новиков", "Морозов", "Петухов" };
            string[] SurnamesW = { "Иванова", "Петрова", "Шишкина", "Масленникова", "Овечкина", "Попова", "Соловьева", "Киселева", "Федорова", "Дорофеева", "Гончарова", "Новикова", "Морозова", "Петухова" };

            Client_LegalEntity client = new Client_LegalEntity();
            int a = rnd.Next();
            if (a % 2 == 0) // фамилия имя
            {
                client.Name = NamesM[rnd.Next(14)];
                client.Surname = SurnamesM[rnd.Next(14)];
            }
            else
            {
                client.Name = NamesW[rnd.Next(14)];
                client.Surname = SurnamesW[rnd.Next(14)];
            }

            string passtr = ""; // паспорт
            for (int i = 0; i < 10; i++)
            {
                a = rnd.Next(10);
                passtr += a.ToString();
            }
            client.Passport = passtr;

            DateTime from = new DateTime(1970, 1, 1, 0, 0, 0); // дата рождения
            DateTime to = new DateTime(2000, 1, 1, 0, 0, 0);
            DateTime birthday = GenRandomDateTime(from, to, rnd);
            client.Birth = birthday.ToShortDateString();
            client.Company = Companies[rnd.Next(3)];
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
