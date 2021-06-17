using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace Bank
{
    [Serializable]
    public class Journal : IEnumerable
    {
        public List<JournalEntry> JournalList = new List<JournalEntry>();

        public IEnumerator GetEnumerator() 
        {
            foreach(JournalEntry Entry in JournalList)
            {
                yield return Entry;
            }
        }

        public Journal()
        {
            
        }
        public int Length
        {
            get { return JournalList.Count();}
        }

        // МЕТОДЫ
        public void SomeEvent(object sourse, CollectionArgumentHandler e)
        {
            JournalEntry OneEntry = new JournalEntry(e.CollectionName, e.InfoOfAction, e.ChangedObject.ToString()); 
            JournalList.Add(OneEntry);                                                                             
            
            // запись событий в файл журнала
            FileStream file;
            try
            {
                file = new FileStream(@"D:\Рабочий стол\Bank\Journals\txt__" + DateTime.Now.ToShortDateString() + ".txt", FileMode.Append); //создаем файловый поток
            }
            catch
            {
                File.Create(@"D:\Рабочий стол\Bank\Journals\txt__" + DateTime.Now.ToShortDateString() + ".txt").Close();
                file = new FileStream(@"D:\Рабочий стол\Bank\Journals\txt__" + DateTime.Now.ToShortDateString() + ".txt", FileMode.Open); //создаем файловый поток
            }
            StreamWriter f = new StreamWriter(file, Encoding.GetEncoding(1251)); // открывает файл Encoding.GetEncoding(1251) - позволяет работать с русским языком
            f.WriteLine(OneEntry);
            f.Close();
        }

        public void OtherEvent(string CollectionName, string InfoOfAction)
        {
            JournalEntry OneEntry = new JournalEntry(CollectionName, InfoOfAction);
            JournalList.Add(OneEntry);

            // запись событий в файл журнала
            FileStream file;
            try
            {
                file = new FileStream(@"D:\Рабочий стол\Bank\Journals\txt__" + DateTime.Now.ToShortDateString() + ".txt", FileMode.Append); //создаем файловый поток
            }
            catch
            {
                File.Create(@"D:\Рабочий стол\Bank\Journals\txt__" + DateTime.Now.ToShortDateString() + ".txt").Close();
                file = new FileStream(@"D:\Рабочий стол\Bank\Journals\txt__" + DateTime.Now.ToShortDateString() + ".txt", FileMode.Open); //создаем файловый поток
            }
            StreamWriter f = new StreamWriter(file, Encoding.GetEncoding(1251)); // открывает файл Encoding.GetEncoding(1251) - позволяет работать с русским языком
            f.WriteLine(OneEntry);
            f.Close();
        }

        public override string ToString()
        {
            string AllEntries = "";
            foreach (JournalEntry x in JournalList)
                AllEntries = AllEntries + "\n----------------------------------\n" + x;
            return AllEntries;
        }
    }
}
