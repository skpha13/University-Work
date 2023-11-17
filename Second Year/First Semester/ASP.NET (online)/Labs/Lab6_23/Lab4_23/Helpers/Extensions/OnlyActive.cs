using Lab4_23.Models;

namespace Lab4_23.Helpers.Extensions
{
    public static class OnlyActive
    {
        public static IQueryable<User> GetActiveUsers(this IQueryable<User> query)
        {
            return query.Where(x => !x.IsDeleted);
        }
    }
}
