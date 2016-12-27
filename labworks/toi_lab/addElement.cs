using System;
using Gtk;
using Npgsql;

namespace labwork
{
	public partial class addElement : Gtk.Window
	{
		DB_stuff dbstuff = new DB_stuff("Server=localhost;Port=5432;User Id=just_user;Password=QWERTY;Database=just_test;");
		public addElement () :
			base (Gtk.WindowType.Toplevel)
		{
			
			this.Build ();
			comboboxentry7.Clear ();
			CellRendererText cell = new CellRendererText();
			comboboxentry7.PackStart(cell, false);
			comboboxentry7.AddAttribute(cell, "text", 0);
			ListStore store = new ListStore(typeof (string));
			comboboxentry7.Model = store;
			store.AppendValues ("Студенты");
			store.AppendValues ("Экзамены");
			store.AppendValues ("Результаты");




		}

		protected void OnComboboxentry7Changed (object sender, EventArgs e)
		{
			//string selectedState = comboboxentry7.SelectedItem.ToString();
			string r = comboboxentry7.ActiveText;
			if (r == "Студенты") {
				label11.Text = "На отчисление";
				label12.Text = "ФИО";
				label13.Text = "Номер зачетки";
				label14.Text = "Номер группы";
			} else if (r == "Экзамены") {
				label11.Text = "Преподователь";
				label12.Text = "Предмет";
				label13.Text = "Номер экзамена";
				label14.Text = "Дата сдачи";
			} else if (r == "Результаты") {
				label11.Text = "Оценка";
				label12.Text = "Номер зачетки";
				label13.Text = "Номер экзамена";
				label14.Text = "Дата сдачи";
			}

		}

		protected void OnDeleteEvent (object sender, DeleteEventArgs a)
		{
			this.Destroy ();
			SecondWindow win2 = new SecondWindow();
			win2.Show ();
		}

		protected void OnButton27Clicked (object sender, EventArgs e)
		{
			string r = comboboxentry7.ActiveText;
			string dest, field0, field1,field2,field3;
			dest = "";
			field0 = "";
			field1 = "";
			field2 = "";
			field3 = "";
			if (r == "Студенты") {
				dest = "students";
				field0 = "expelling";
				field1 = "fio";
				field2 = "studcard_number";
				field3 = "group_number";
				dbstuff.setCommand = " BEGIN; Insert into "+ dest + " ( " + field0 + ", " + field1 +
 					" ," + field2 + " ," + field3 + " ) values ( '" + entry12.Text + "' , '" +
					entry11.Text + "' ," + entry10.Text + " , " + entry9.Text + " ); COMMIT;";
			} else if (r == "Экзамены") {
				dest = "exams";
				field0 = "lector_name";
				field1 = "exam_name";
				field2 = "exam_number";
				field3 = "pass_time";
				dbstuff.setCommand = " BEGIN; Insert into "+ dest + " ( " + field0 + ", " + field1 +
					" ," + field2 + " ," + field3 + " ) values ( '" + entry12.Text + "' , '" +
					entry11.Text + "' ," + entry10.Text + " , '" + entry9.Text + "' ); COMMIT;";
			} else if (r == "Результаты") {
				dest = "exams_taking";
				field0 = "mark";
				field1 = "studcard_number";
				field2 = "exam_number";
				field3 = "pass_time";
				dbstuff.setCommand = " BEGIN; Insert into "+ dest + " ( " + field0 + ", " + field1 +
					" ," + field2 + " ," + field3 + " ) values ( " + entry12.Text + " , " +
					entry11.Text + " ," + entry10.Text + " , '" + entry9.Text + "' ); COMMIT;";
			}

			NpgsqlDataReader reader;

			dbstuff.conn.Open();

			reader =  dbstuff.comm.ExecuteReader();

			Console.WriteLine (reader.ToString() );


			Console.WriteLine (dbstuff.setCommand);

			dbstuff.conn.Close();
		}
	}
}

