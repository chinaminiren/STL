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
            for (int i = 20; i < 30; ++i)
            {
                sb.Append("[");

                DateTime utcNow = DateTime.Now.ToUniversalTime();
                double utc = ConvertDateTimeInt(utcNow) + i * 1000;
                sb.Append(utc.ToString());
                sb.Append(",");
                sb.Append((i * 10).ToString());
                sb.Append("]");
                if(i<99)
                  sb.Append(",");
            }
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