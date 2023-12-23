using Lab9.Models;

namespace Lab9.Helpers.Extensions
{
    public static class OnlyActive
    {
        public static IQueryable<User> GetActiveUser(this IQueryable<User> query)
        {
            return query.Where(x => !x.IsDeleted);
        }
    }
}
