using Lab3_23.Models.Base;

namespace Lab3_23.Models
{
    public class Student: BaseEntity
    {
        public string? Name { get; set; }
        public int Age { get; set; }
    }
}
