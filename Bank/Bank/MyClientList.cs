using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bank
{
    [Serializable]
    class MyClientList : List<Client>, IEnumerable
    {
        public int Length
        {
            get { return base.Count; }
        }

        public new IEnumerator GetEnumerator()
        {
            foreach (Client client in new MyClientList())
            {
                yield return client;
            }
        }

        public void AddClient(Client client)
        {
            base.Add(client);
        }

        public void RemoveClient(Client client)
        {
            base.Remove(client);
        }

        public void ClearList()
        {
            base.Clear();
        }

        public void AddCredit(Client client, string sum, string period, string rate)
        {
            client.NewCredit(sum, period, rate);
        }

        public void AddDeposit(Client client, string sum, string period, string rate)
        {
            client.NewDeposit(sum, period, rate);
        }
    }
}
