using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bank
{
    [Serializable]
    public class JournalEntry 
    {
        public string Date { get; set; }
        public string CollectionName { get; set; } // название коллекции - отделения банка
        public string InfoOfAction { get; set; }   // тип изменения
        public string Client { get; set; }  // измененный объект

        public JournalEntry(string BB, string EI, string C)
        {
            DateTime dt = DateTime.Now;

            Date = dt.ToShortTimeString();
            CollectionName = BB;
            InfoOfAction = EI;
            Client = C;
        }

        public JournalEntry(string BB, string EI)
        {
            DateTime dt = DateTime.Now;

            Date = dt.ToLongTimeString();
            CollectionName = BB;
            InfoOfAction = EI;
        }

        public override string ToString()
        {
            if (Client == null) return $"\n{Date} - {InfoOfAction}";
            return $"\n{Date} - Отделение: {CollectionName} \nСобытие: {InfoOfAction} \nКлиент: {Client}";
        }
    }
}
