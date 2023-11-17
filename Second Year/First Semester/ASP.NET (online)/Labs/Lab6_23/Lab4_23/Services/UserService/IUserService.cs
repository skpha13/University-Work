using Lab4_23.Models;
using Lab4_23.Models.DTOs;

namespace Lab4_23.Services.UserService
{
    public interface IUserService
    {
        Task<List<UserDto>> GetAllUsers();

        UserDto GetUserByUsername(string username);
    }
}
