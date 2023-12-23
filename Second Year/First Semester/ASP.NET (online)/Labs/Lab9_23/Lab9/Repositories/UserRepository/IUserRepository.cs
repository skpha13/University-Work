using Lab9.Models;
using Lab9.Repositories.GenericRepository;

namespace Lab9.Repositories.UserRepository
{
    public interface IUserRepository: IGenericRepository<User>
    {
        Task<User> FindByUsername(string username);
        //Task<User> FindByUsernameAndPassword(string username, string password);


        Task<List<User>> FindAll();

        Task<List<User>> FindAllActive();

    }
}
