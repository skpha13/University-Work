using Lab4_23.Helpers.Seeders;
using Lab4_23.Repositories.UserRepository;
using Lab4_23.Services.UserService;

namespace Lab4_23.Helpers.Extensions
{
    public static class ServiceExtentions
    {
        public static IServiceCollection AddRepositories(this IServiceCollection services)
        {
            services.AddTransient<IUserRepository, UserRepository>();

            return services;
        }

        public static IServiceCollection AddServices(this IServiceCollection services)
        {
            services.AddTransient<IUserService, UserService>();

            return services;
        }

        public static IServiceCollection AddSeeders (this IServiceCollection services)
        {
            services.AddTransient<UsersSeeder>();

            return services;
        }
    }
}
