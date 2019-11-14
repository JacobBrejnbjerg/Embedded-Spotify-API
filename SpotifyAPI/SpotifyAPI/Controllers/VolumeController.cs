using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Options;
using SpotifyAPI.Lib;
using SpotifyAPI.Models;
using SpotifyAPI.Settings;

namespace SpotifyAPI.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class VolumeController : ControllerBase
    {
        private readonly SpotifyAPISettings _spotifyAPISettings;

        public VolumeController(IOptions<SpotifyAPISettings> spotifyApiSettings)
        {
            _spotifyAPISettings = spotifyApiSettings.Value;
        }

        /// <summary>
        /// Sets the volume of Spotify
        /// </summary>
        /// <param name="volume">Volume between 0 and 100%</param>
        /// <returns>HTTP Statuscode of whether it went well or not</returns>
        [HttpGet]
        public async Task<IActionResult> Get(int volume)
        {
            HttpStatusCode status = await HttpCaller.Put(_spotifyAPISettings.SpotifyUrl + "/volume" +
                                                                        "?volume_percent=" + volume +
                                                                        "&device_id=" + _spotifyAPISettings.DeviceID,
                                                        _spotifyAPISettings.AccessToken,
                                                        null);

            return StatusCode((int)status);
        }
    }
}