using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1_24
{
    public class Class1: Interface1
    {
        public string FirstName { get; set; }
        public string LastName { get; set; }

        public string Title { get; set; }
        public string Description { get; set; }

        public int Value1 { get; set; } = 1;
        public int Value2 { get; set; } = 2;

        public List<string> Tags { get; set; }

        public string CompleteName
        {
            get { return FirstName + " " + LastName; }
            set { CompleteName = FirstName + " " + LastName; }
        }

        public void Method1()
        {
            Console.WriteLine("Method 1");
        }

        public int Method2(int extraValue = 0)
        {
            return Value1 + Value2 + extraValue;
        }

    }
}
