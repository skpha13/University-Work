using Lab9.Models.Base;

namespace Lab9.Repositories.GenericRepository
{
    public interface IGenericRepository<TEntity> where TEntity : BaseEntity
    {
        // Get all data
        Task<List<TEntity>> GetAll();
        
        // Create data
        void Create(TEntity entity);
        Task CreateAsync(TEntity entity);

        void CreateRange(IEnumerable<TEntity> entities);
        Task CreateRangeAsync(IEnumerable<TEntity> entities);

        // Update
        void Update(TEntity entity);
        void UpdateRange(IEnumerable<TEntity> entities);

        // Delete 
        void Delete(TEntity entity);
        void DeleteRange(IEnumerable<TEntity> entities);

        // Find
        TEntity FindById(Guid id);
        Task<TEntity> FindByIdAsync(Guid id);


        // Save
        bool Save();
        Task<bool> SaveAsync();
    }
}
