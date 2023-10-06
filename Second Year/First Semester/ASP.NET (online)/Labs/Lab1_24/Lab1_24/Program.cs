using Lab1_24;

var a = new object[] { 1, 2, 3 };
var b = new object[] {"a", "b", "c"};

for (int i = 0; i < a.Length; i++)
{
    Console.WriteLine(a[i]);
}

foreach(string i in b)
{
    Console.WriteLine(i);
}

// version 1
List<object> list = new()
{
    "1a",
    "2b",
    "3c"
};

// version 2; same logic
List<object> list2 = new List<object>();
list.Add("21a");
list.Add("22b");
list.Add("23c");

var classObject1 = new Class1 
{ 
    FirstName = "FirstName 1", 
    LastName= "LastName 1"
};

Class1 classObject2 = new Class1();
classObject2.FirstName = "FirstName 2";
classObject2.LastName = "LastName 2";

Console.WriteLine(classObject1.CompleteName);
Console.WriteLine(classObject2.CompleteName);

Console.WriteLine(classObject1.ToString());

Class1 classObject3 = null;
// Console.WriteLine(classObject3.Description); -> gives error
Console.WriteLine(classObject3?.Description);

classObject1.Method1();
var result = classObject1.Method2();
Console.WriteLine(result);

var result2 = classObject1.Method2(7);
Console.WriteLine(result2);