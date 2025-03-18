using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_MAP_02
{
    public class UserDataContext
    {
        public User CurrentUser { get; set; }
        public ObservableCollection<User> Users { get; set; }
        public UserDataContext()
        {
            CurrentUser = new User() { Username = "ana", Password = "123" };
            Users = new ObservableCollection<User>();
        }
    }
}
