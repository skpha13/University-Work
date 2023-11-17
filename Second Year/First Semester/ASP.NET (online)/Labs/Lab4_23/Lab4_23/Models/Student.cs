using Lab4_23.Models.Base;

namespace Lab4_23.Models
{
    public class Student: BaseEntity
    {
        public string? FirstName { get; set; }
        public string? LastName { get; set; }
        public int Age { get; set; }
        public string? Email { get; set; }
    }
}
