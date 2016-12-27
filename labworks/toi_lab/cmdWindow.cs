using System;
using Npgsql;
using Gtk;

namespace labwork
{
	public partial class cmdWindow : Gtk.Window
	{
		DB_stuff dbstuff = new DB_stuff("Server=localhost;Port=5432;User Id=just_user;Password=QWERTY;Database=just_test;");
		public cmdWindow () :
			base (Gtk.WindowType.Toplevel)
		{
			this.Build ();
		}

		protected void OnButton10Clicked (object sender, EventArgs e)
		{
			NpgsqlDataReader reader;

			dbstuff.conn.Open();
			dbstuff.setCommand = textview3.Buffer.Text;

			reader =  dbstuff.comm.ExecuteReader();

			textview2.Buffer.Text = "";
			while (reader.Read ()) {
				for (int i = 0; i < reader.FieldCount; i++) {
					if (reader.GetString (i) == null)
						continue;
					else textview2.Buffer.Text += reader.GetString(i) + "\t" + "\t";
				}
				textview2.Buffer.Text += "\n";
			}

			dbstuff.conn.Close();
		}

		protected void OnDeleteEvent (object sender, DeleteEventArgs a)
		{
			this.Destroy ();
			SecondWindow win2 = new SecondWindow();
			win2.Show ();
		}
	}
}

