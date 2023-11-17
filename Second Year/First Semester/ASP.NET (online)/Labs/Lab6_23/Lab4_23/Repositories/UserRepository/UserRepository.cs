using Lab4_23.Data;
using Lab4_23.Helpers.Extensions;
using Lab4_23.Models;
using Lab4_23.Repositories.GenericRepository;

namespace Lab4_23.Repositories.UserRepository
{
    public class UserRepository : GenericRepository<User>, IUserRepository
    {
        public UserRepository(Lab4Context lab4Context) : base(lab4Context)
        {
        }

        public List<User> FindAllActive()
        {
            return _table.GetActiveUsers().ToList();
        }

        public User FindByUsername(string username)
        {
            return _table.FirstOrDefault(u => u.Username.Equals(username));
        }
    }
}
