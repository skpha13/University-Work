using Lab9.Models;
using Microsoft.EntityFrameworkCore;

namespace Lab9.Data
{
    public class Lab9Context: DbContext
    {
        public DbSet<User> Users { get; set; }
        public Lab9Context(DbContextOptions<Lab9Context> options) : base(options) { }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
           
            base.OnModelCreating(modelBuilder);
        }
    }
}
