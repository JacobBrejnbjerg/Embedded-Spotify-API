using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SpotifyAPI.Models
{
    public class Player
    {
        public long Timestamp { get; set; }
        public Device Device { get; set; }
        public string Progress_ms { get; set; }
        public bool Is_playing { get; set; }
        public string Currently_playing_type { get; set; }
        public Actions Actions { get; set; }
        public Item Item { get; set; }
        public bool Shuffle_state { get; set; }
        public string Repeat_state { get; set; }
        public Context Context { get; set; }
    }

    public class Device
    {
        public string id { get; set; }
        public bool is_active { get; set; }
        public bool is_restricted { get; set; }
        public string name { get; set; }
        public string type { get; set; }
        public int volume_percent { get; set; }
    }
}
