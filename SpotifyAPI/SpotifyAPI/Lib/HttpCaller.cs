using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Threading.Tasks;

namespace SpotifyAPI.Lib
{
    public class HttpCaller
    {
        public static async Task<T> Get<T>(string url, string token)
        {
            HttpClient client = new HttpClient();
            client.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", token);
            string jsonResult = await client.GetStringAsync(url);
            return JsonConvert.DeserializeObject<T>(jsonResult);
        }

        public static async Task<HttpStatusCode> Post(string url, string token, HttpContent content)
        {
            HttpClient client = new HttpClient();
            client.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", token);
            HttpResponseMessage msg = await client.PostAsync(url, content);
            return msg.StatusCode;
        }

        public static async Task<HttpStatusCode> Put(string url, string token, HttpContent content)
        {
            HttpClient client = new HttpClient();
            client.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", token);
            HttpResponseMessage msg = await client.PutAsync(url, content);
            return msg.StatusCode;
        }
    }
}
