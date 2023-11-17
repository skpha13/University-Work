using Lab3_23.Data;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace Lab3_23.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class DatabaseController : ControllerBase
    {
        private readonly Lab3Context _lab3Context;
        public DatabaseController(Lab3Context lab3Context) {
            _lab3Context = lab3Context;
        }

        [HttpGet]
        public async Task<IActionResult> Get()
        {
            return Ok(await _lab3Context.Students.ToListAsync());
        }
    }
}
