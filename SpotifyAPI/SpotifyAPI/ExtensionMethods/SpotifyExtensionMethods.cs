using SpotifyAPI.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SpotifyAPI.ExtensionMethods
{
    public static class SpotifyExtensionMethods
    {
        public static SpotifyReply ToSpotifyReply(this Player player)
        {
            return new SpotifyReply()
            {
                SongName = player.Item.name,
                Artist = String.Join(", ", player.Item.artists.Select(a => a.name)),
                Volume = player.Device.volume_percent,
                Seconds = Convert.ToInt32(player.Item.duration_ms) / 1000,
                PlayedSeconds = Convert.ToInt32(player.Progress_ms) / 1000,
            };
        }
    }
}
