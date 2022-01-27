using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Perudo_UI.Model
{
    public class Player
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public int NumberOfDice { get; set; }
        public bool IsReady { get; set; }

        public Player(int id, bool isReady, string name, int numberOfDice)
        {
            Id = id;
            IsReady = isReady;
            Name = name;
            NumberOfDice = numberOfDice;
        }
    }
}
