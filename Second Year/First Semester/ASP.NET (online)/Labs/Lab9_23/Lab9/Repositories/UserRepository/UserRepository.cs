using Lab9.Data;
using Lab9.Helpers.Extensions;
using Lab9.Models;
using Lab9.Repositories.GenericRepository;
using Microsoft.EntityFrameworkCore;

namespace Lab9.Repositories.UserRepository
{
    public class UserRepository : GenericRepository<User>, IUserRepository
    {
        public UserRepository(Lab9Context lab4Context) : base(lab4Context)
        {
        }

        public async Task<List<User>> FindAll()
        {
            return await _table.ToListAsync();
        }

        public async Task<List<User>> FindAllActive()
        {
            return await _table.GetActiveUser().ToListAsync();
        }

        public async Task<User> FindByUsername(string username)
        {
            return (await _table.FirstOrDefaultAsync(u => u.Username.Equals(username)))!;
        }

        //public  async Task<User> FindByUsernameAndPassword(string username, string password)
        //{
        //    return (await _table.FirstOrDefaultAsync(u => u.Username.Equals(username) && u.Password.Equals(password)))!;
        //}
    }
}
