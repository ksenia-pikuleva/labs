using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bank
{
    [Serializable]
    public class CollectionArgumentHandler : EventArgs
    {
        public string CollectionName { get; set; } // название коллекции - отделения банка
        public string InfoOfAction { get; set; }   // тип изменения
        public Client ChangedObject { get; set; }  // измененный объект

        public CollectionArgumentHandler(string CN, string IOA, Client CO)
        {
            CollectionName = CN;
            InfoOfAction = IOA;
            ChangedObject = CO;
        }

        public override string ToString()
        {
            return $"Отделение-{CollectionName} \nИзменение-{InfoOfAction} \nКлиент-{ChangedObject.ToString()}";
        }
    }
}
