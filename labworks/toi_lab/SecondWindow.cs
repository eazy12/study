using System;
using Gtk;
using Npgsql;

namespace labwork
{
	public partial class SecondWindow : Gtk.Window
	{
		DB_stuff dbstuff = new DB_stuff("Server=127.0.0.1;Port=5432;User Id=just_user;Password=QWERTY;Database=just_test;");
		public SecondWindow () :
			base (Gtk.WindowType.Toplevel)
		{
			this.Build ();

		}

		protected void OnButton5Clicked (object sender, EventArgs e)
		{
			this.Destroy ();
			MainWindow win = new MainWindow ();
			win.Show ();
		}

		protected void OnButton2Clicked (object sender, EventArgs e)
		{
			this.Destroy ();
			Application.Quit ();
		}

		protected void OnButton1Clicked (object sender, EventArgs e)
		{
			try
			{
				
				NpgsqlDataReader reader2;
				//dbstuff.setCommand = textview1.Buffer.Text ;

				dbstuff.conn.Open();
				reader2 =  dbstuff.comm.ExecuteReader();


				/*while(reader2.Read())
				{	
					for( int i=0; i < reader2.FieldCount; i++)
					{
						textview2.Buffer.Text += reader2.GetString(i) + "\t";
					}
					textview2.Buffer.Text += "\n";
				}*/
				dbstuff.conn.Close();
			}
			catch 
			{
				dbstuff.conn.Close();
			}

		}

		protected void OnLabel4DeleteEvent (object o, DeleteEventArgs args)
		{
			Application.Quit ();
			args.RetVal = true;
		}

		protected void OnDeleteEvent (object sender, DeleteEventArgs a)
		{
			Application.Quit ();
			a.RetVal = true;
		}
	
		protected void OnButton14Clicked (object sender, EventArgs e)
		{
			addElement win3 = new addElement();
			win3.Show ();
			this.Destroy();
		}

		protected void OnButton15Clicked (object sender, EventArgs e)
		{
			deleteElement win3 = new deleteElement();
			win3.Show ();
			this.Destroy();
		}

		protected void OnButton16Clicked (object sender, EventArgs e)
		{
			cmdWindow win3 = new cmdWindow();
			win3.Show ();
			this.Destroy();
		}
	}
}

