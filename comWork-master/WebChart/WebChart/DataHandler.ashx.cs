using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Text;

namespace WebChart
{
    /// <summary>
    /// Summary description for DataHandler
    /// </summary>
    public class DataHandler : IHttpHandler
    {

        public void ProcessRequest(HttpContext context)
        {
            HttpResponse res = context.Response;
            HttpRequest req = context.Request;

            StringBuilder sb = new StringBuilder();
            sb.Append("[");

            sb.Append("[");
            long dt = DateTime.Now.Ticks;
            //double utc = ConvertDateTimeInt(utcNow);
            sb.Append(dt.ToString());
            sb.Append(",");
            sb.Append((10).ToString());
            sb.Append("]");

            sb.Append(",");

            sb.Append("[");
            dt = DateTime.Now.AddSeconds(1).Ticks;
            //double utc = ConvertDateTimeInt(utcNow);
            sb.Append(dt.ToString());
            sb.Append(",");
            sb.Append((20).ToString());
            sb.Append("]");

            sb.Append("]");

            string json = sb.ToString();
            res.Write(json);
            res.ContentType = "text/plain";
            res.End();

        }

        public bool IsReusable
        {
            get
            {
                return false;
            }
        }

        public double ConvertDateTimeInt(System.DateTime time)
        {
            double intResult = 0;
            System.DateTime startTime = TimeZone.CurrentTimeZone.ToLocalTime(new System.DateTime(1970, 1, 1));
            intResult = (time - startTime).TotalSeconds;
            return intResult;
        }
    }
}