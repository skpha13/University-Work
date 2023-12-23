using Lab9.Models.Base;
using Lab9.Models.Enums;
using System.Text.Json.Serialization;

namespace Lab9.Models
{
    public class User: BaseEntity
    {
        public string FirstName { get; set; }

        public string LastName { get; set; }

        public string Email { get; set; }

        public string Username { get; set; }

        [JsonIgnore]
        public string Password { get; set; }

        public Role Role { get; set; }
    }
}
