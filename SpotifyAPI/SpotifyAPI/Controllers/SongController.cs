using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore.Internal;
using Microsoft.Extensions.Options;
using SpotifyAPI.ExtensionMethods;
using SpotifyAPI.Lib;
using SpotifyAPI.Models;
using SpotifyAPI.Settings;

namespace SpotifyAPI.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class SongController : ControllerBase
    {
        private readonly SpotifyAPISettings _spotifyAPISettings;

        public SongController(IOptions<SpotifyAPISettings> spotifyApiSettings)
        {
            _spotifyAPISettings = spotifyApiSettings.Value;
        }


        /// <summary>
        /// Gets data from the Spotify API
        /// </summary>
        /// <returns>SpotifyReply object of current playing song</returns>
        [HttpGet]
        public async Task<ActionResult<SpotifyReply>> Get()
        {
            Player player = await HttpCaller.Get<Player>(_spotifyAPISettings.SpotifyUrl,
                                                            _spotifyAPISettings.AccessToken);

            SpotifyReply spotifyReply = player.ToSpotifyReply();

            return Ok(spotifyReply);
        }


        /// <summary>
        /// Skips to next song in Spotify API
        /// </summary>
        /// <returns>SpotifyReply object with data of new song</returns>
        [HttpGet("Next")]
        public async Task<ActionResult<SpotifyReply>> Next()
        {
            HttpStatusCode status = await HttpCaller.Post(_spotifyAPISettings.SpotifyUrl + "/next?device_id=" + _spotifyAPISettings.DeviceID,
                                                        _spotifyAPISettings.AccessToken,
                                                        null);

            Player player = await HttpCaller.Get<Player>(_spotifyAPISettings.SpotifyUrl,
                                                            _spotifyAPISettings.AccessToken);

            SpotifyReply spotifyReply = player.ToSpotifyReply();

            return Ok(spotifyReply);
        }


        /// <summary>
        /// Goes to previous song in Spotify API
        /// </summary>
        /// <returns>SpotifyReply object with data of new song</returns>
        [HttpGet("Previous")]
        public async Task<ActionResult<SpotifyReply>> Previous()
        {
            HttpStatusCode status = await HttpCaller.Post(_spotifyAPISettings.SpotifyUrl + "/previous?device_id=" +_spotifyAPISettings.DeviceID,
                                                        _spotifyAPISettings.AccessToken,
                                                        null);

            Player player = await HttpCaller.Get<Player>(_spotifyAPISettings.SpotifyUrl,
                                                             _spotifyAPISettings.AccessToken);

            SpotifyReply spotifyReply = player.ToSpotifyReply();

            return Ok(spotifyReply);
        }

        /// <summary>
        /// Pauses currently playing song
        /// </summary>
        /// <returns>HTTP Statuscode of whether it went well or not</returns>
        [HttpGet("Pause")]
        public async Task<IActionResult> Pause()
        {
            HttpStatusCode status = await HttpCaller.Put(_spotifyAPISettings.SpotifyUrl + "/pause?device_id=" +_spotifyAPISettings.DeviceID,
                                                        _spotifyAPISettings.AccessToken,
                                                        null);

            return StatusCode((int)status);
        }

        /// <summary>
        /// Resumes the paused song song
        /// </summary>
        /// <returns>HTTP Statuscode of whether it went well or not</returns>
        [HttpGet("Play")]
        public async Task<IActionResult> Play()
        {

            HttpStatusCode status = await HttpCaller.Put(_spotifyAPISettings.SpotifyUrl + "/play?device_id=" + _spotifyAPISettings.DeviceID,
                                                        _spotifyAPISettings.AccessToken,
                                                        null);

            return StatusCode((int)status);
        }
    }
}