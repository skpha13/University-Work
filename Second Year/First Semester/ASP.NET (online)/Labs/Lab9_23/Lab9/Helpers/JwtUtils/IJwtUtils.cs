using Lab9.Models;

namespace Lab9.Helpers.JwtUtil
{
    public interface IJwtUtils
    {
        public string GenerateJwtToken(User user);
        public Guid? GetUserId(string? token);
    }
}
