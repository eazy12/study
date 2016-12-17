using System;
using Gtk;
using Npgsql;
using labwork;
using GLib;


namespace labwork
{
public partial class MainWindow: Gtk.Window
	{
		DB_stuff dbstuff = new DB_stuff("Server=127.0.0.1;Port=5432;User Id=just_user;Password=QWERTY;Database=just_test;");

		public MainWindow () : base (Gtk.WindowType.Toplevel)
		{
			Build ();
			entry2.Visibility = false;

		}

		protected void OnDeleteEvent (object sender, DeleteEventArgs a)
		{
			Application.Quit ();
			a.RetVal = true;
		}

		protected void OnButton6Clicked (object sender, EventArgs e)
		{
			try
			{
				dbstuff.setCommand = "Select password From tech_stuff WHERE login ='" + entry1.Text + "'" ;
				NpgsqlDataReader reader1;

				dbstuff.conn.Open();
	
				reader1 =  dbstuff.comm.ExecuteReader();
				reader1.Read();
				string password = reader1.GetString(0);
				if ( comparing(password, entry2.Text) == -1)
				{
					label1.Show();
					label1.Text = "Неверный пароль";
				}
				else
				{
					SecondWindow win2 = new SecondWindow();
					win2.Show ();
					this.Destroy();
				}
	
				dbstuff.conn.Close();
			}
			catch
			{
				dbstuff.conn.Close();
			}
		}

		public int comparing(string s1, string s2)
		{
			int i;
			for (i = 0; i < Math.Min(s2.Length,s1.Length) ; i++)
			{
				if (s1[i] != s2[i]) return -1;
			}
			return 0;
		}

		protected void OnButton3Clicked (object sender, EventArgs e)
		{
			this.Destroy ();
			Application.Quit ();
		}
	}
}
