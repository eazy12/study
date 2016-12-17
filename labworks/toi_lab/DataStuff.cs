using System;
using Npgsql;

namespace labwork
{
	public class DB_stuff
	{
		public string connectParam;
		public string sql;
		public NpgsqlConnection conn;
		public NpgsqlCommand comm;

		public DB_stuff(string s1)
		{
			this.sql = "Select * from USERS";
			this.connectParam = s1;
			this.conn = new NpgsqlConnection(this.connectParam);
			this.comm = new NpgsqlCommand(this.sql, this.conn);
		}

		public string setCommand
		{
			get
			{
				return this.comm.CommandText;
			}
			set
			{
				this.comm.CommandText = value;
			}
		}
	}

}

