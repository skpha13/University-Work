using Lab4_23.Models.Base;
using Lab4_23.Models.Enums;

namespace Lab4_23.Models
{
    public class User: BaseEntity
    {
        public string FirstName { get; set; }
        public string LastName { get; set; }

        public string Email { get; set; }
        public string Username { get; set; }
        public string Password { get; set; }

        public Role Role { get; set; }
    }
}
