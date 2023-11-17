using Lab4_23.Models;
using Lab4_23.Repositories.GenericRepository;

namespace Lab4_23.Repositories.StudentRepository
{
    public interface IStudentRepository: IGenericRepository<Student>
    {
        List<Student> OrderByAge(int age);
    }
}
