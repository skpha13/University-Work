
using Lab9.Data.DTOs;
using Lab9.Models;
using Lab9.Models.Enums;

namespace Lab9.Services.UserService
{
    public interface IUserService
    {
        Task<UserLoginResponse> Login(UserLoginDto user);
        User GetById(Guid id);

        Task<bool> Register(UserRegisterDto userRegisterDto, Role userRole);
    }
}
