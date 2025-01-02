using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace DemoZiua1Server.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class UserController : ControllerBase
    {
        private List<User> userList = new List<User>();

        [HttpGet(Name = "Get")]
        public IEnumerable<User> Get()
        {
            return userList;
        }
    }
}
