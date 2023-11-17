using Lab4_23.Models;
using Lab4_23.Repositories.GenericRepository;

namespace Lab4_23.Repositories.UserRepository
{
    public interface IUserRepository: IGenericRepository<User>
    {
        User FindByUsername(string username);

        List<User> FindAllActive();
    }
}
