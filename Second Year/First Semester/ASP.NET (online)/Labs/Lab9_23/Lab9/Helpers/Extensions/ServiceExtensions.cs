using Lab9.Helpers.JwtUtil;
using Lab9.Helpers.JwtUtil;
using Lab9.Repositories.UserRepository;
using Lab9.Services.UserService;

namespace Lab9.Helpers.Extensions
{
    public static class ServiceExtensions
    {
        public static IServiceCollection AddRepositories (this IServiceCollection services)
        {
            services.AddTransient<IUserRepository, UserRepository>();

            return services;
        }

        public static IServiceCollection AddServices(this IServiceCollection services)
        {
            services.AddTransient<IUserService, UserService>();

            return services;
        }

        public static IServiceCollection AddHelpers(this IServiceCollection services)
        {
            services.AddTransient<IJwtUtils, JwtUtils>();

            return services;
        }
    }
}
