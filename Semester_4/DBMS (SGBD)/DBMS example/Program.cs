using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SqlClient;

namespace DBMS_example
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string conString = "Data Source=Tere_Roxy;" + "Initial Catalog=Music Sheet Platform;Integrated Security=True";
            SqlConnection con = new SqlConnection(conString);
            con.Open();
            string nrSheets = "SELECT * FROM MusicSheet";
            SqlCommand cmd = new SqlCommand(nrSheets, con);

            //SqlDataReader
            using (SqlDataReader reader = cmd.ExecuteReader())
            {
                while (reader.Read())
                {
                    Console.WriteLine("{0}, {1}", reader[0], reader[1]);
                }
            }

            //wait to press any key
            Console.ReadLine();

            con.Close();
        }
    }
}
