using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bank
{
    public delegate void CollectionHandler(object source, CollectionArgumentHandler args);

    [Serializable]
    class MyClientList_events : MyClientList 
    {
        public string BankBranchName { get; set; }    // имя коллекции
        public event CollectionHandler ChangingEvent; // событие
        
        public MyClientList_events(string CollectionName):base() 
        {
            BankBranchName = CollectionName;
        }

        public new void AddClient(Client client)
        {
            ChangingEvent?.Invoke(this, new CollectionArgumentHandler(BankBranchName, "Добавлен клиент: ", client));
            base.Add(client);
        }

        public new void RemoveClient(Client client)
        {
            ChangingEvent?.Invoke(this, new CollectionArgumentHandler(BankBranchName, "Удален клиент: ", client));
            base.Remove(client);
        }

        public new void AddCredit(Client client, string sum, string period, string rate)
        {
            ChangingEvent?.Invoke(this, new CollectionArgumentHandler(BankBranchName, "Взят кредит! ", client));
            base.AddCredit(client, sum, period, rate);
        }

        public new void AddDeposit(Client client, string sum, string period, string rate)
        {
            ChangingEvent?.Invoke(this, new CollectionArgumentHandler(BankBranchName, "Открыт вклад! ", client));
            base.AddDeposit(client, sum, period, rate);
        }

        public new void ClearList()
        {
            base.ClearList();
        }
    }
}
