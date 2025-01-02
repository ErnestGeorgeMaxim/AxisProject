namespace DemoZiua1Server.Models
{
    public class User
    {
        public string? Name { get; set; }
        public string? Email { get; set; }
        public int Age { get; set; }

        User()
        {
            this.Age = 0;
            this.Email = "";
            this.Name = "";
        }

        User(string Name, string Email, int Age)
        {
            this.Age = Age;
            this.Email = Email;
            this.Name = Name;
        }
    }
}
