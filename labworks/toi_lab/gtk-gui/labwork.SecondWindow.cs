
// This file has been generated by the GUI designer. Do not modify.
namespace labwork
{
	public partial class SecondWindow
	{
		private global::Gtk.UIManager UIManager;
		
		private global::Gtk.Action newAction;
		
		private global::Gtk.Action deleteAction;
		
		private global::Gtk.Action refreshAction;
		
		private global::Gtk.Action Action;
		
		private global::Gtk.VBox vbox1;
		
		private global::Gtk.VPaned vpaned15;
		
		private global::Gtk.VPaned vpaned17;
		
		private global::Gtk.Button button14;
		
		private global::Gtk.VPaned vpaned18;
		
		private global::Gtk.VPaned vpaned19;
		
		private global::Gtk.Button button15;
		
		private global::Gtk.VPaned vpaned16;
		
		private global::Gtk.VPaned vpaned20;
		
		private global::Gtk.Button button16;

		protected virtual void Build ()
		{
			global::Stetic.Gui.Initialize (this);
			// Widget labwork.SecondWindow
			this.UIManager = new global::Gtk.UIManager ();

			this.AddAccelGroup (this.UIManager.AccelGroup);
			this.Name = "labwork.SecondWindow";
			this.Title = global::Mono.Unix.Catalog.GetString ("SecondWindow");
			this.WindowPosition = ((global::Gtk.WindowPosition)(4));
			this.DefaultWidth = 750;
			this.DefaultHeight = 750;
			// Container child labwork.SecondWindow.Gtk.Container+ContainerChild
			this.vbox1 = new global::Gtk.VBox ();
			this.vbox1.Name = "vbox1";
			this.vbox1.Spacing = 6;
			// Container child vbox1.Gtk.Box+BoxChild
			this.vpaned15 = new global::Gtk.VPaned ();
			this.vpaned15.CanFocus = true;
			this.vpaned15.Name = "vpaned15";
			this.vpaned15.Position = 11;
			// Container child vpaned15.Gtk.Paned+PanedChild
			this.vpaned17 = new global::Gtk.VPaned ();
			this.vpaned17.CanFocus = true;
			this.vpaned17.Name = "vpaned17";
			this.vpaned17.Position = 107;
			// Container child vpaned17.Gtk.Paned+PanedChild
			this.button14 = new global::Gtk.Button ();
			this.button14.CanFocus = true;
			this.button14.Name = "button14";
			this.button14.UseUnderline = true;
			this.button14.Label = global::Mono.Unix.Catalog.GetString ("Добавление записи");
			this.vpaned17.Add (this.button14);
			global::Gtk.Paned.PanedChild w2 = ((global::Gtk.Paned.PanedChild)(this.vpaned17 [this.button14]));
			w2.Resize = false;
			this.vpaned15.Add (this.vpaned17);
			this.vbox1.Add (this.vpaned15);
			global::Gtk.Box.BoxChild w4 = ((global::Gtk.Box.BoxChild)(this.vbox1 [this.vpaned15]));
			w4.Position = 0;
			// Container child vbox1.Gtk.Box+BoxChild
			this.vpaned18 = new global::Gtk.VPaned ();
			this.vpaned18.CanFocus = true;
			this.vpaned18.Name = "vpaned18";
			this.vpaned18.Position = 10;
			// Container child vpaned18.Gtk.Paned+PanedChild
			this.vpaned19 = new global::Gtk.VPaned ();
			this.vpaned19.CanFocus = true;
			this.vpaned19.Name = "vpaned19";
			this.vpaned19.Position = 98;
			// Container child vpaned19.Gtk.Paned+PanedChild
			this.button15 = new global::Gtk.Button ();
			this.button15.CanFocus = true;
			this.button15.Name = "button15";
			this.button15.UseUnderline = true;
			this.button15.Label = global::Mono.Unix.Catalog.GetString ("Удаление записи");
			this.vpaned19.Add (this.button15);
			global::Gtk.Paned.PanedChild w5 = ((global::Gtk.Paned.PanedChild)(this.vpaned19 [this.button15]));
			w5.Resize = false;
			this.vpaned18.Add (this.vpaned19);
			this.vbox1.Add (this.vpaned18);
			global::Gtk.Box.BoxChild w7 = ((global::Gtk.Box.BoxChild)(this.vbox1 [this.vpaned18]));
			w7.Position = 1;
			// Container child vbox1.Gtk.Box+BoxChild
			this.vpaned16 = new global::Gtk.VPaned ();
			this.vpaned16.CanFocus = true;
			this.vpaned16.Name = "vpaned16";
			this.vpaned16.Position = 10;
			// Container child vpaned16.Gtk.Paned+PanedChild
			this.vpaned20 = new global::Gtk.VPaned ();
			this.vpaned20.CanFocus = true;
			this.vpaned20.Name = "vpaned20";
			this.vpaned20.Position = 92;
			// Container child vpaned20.Gtk.Paned+PanedChild
			this.button16 = new global::Gtk.Button ();
			this.button16.CanFocus = true;
			this.button16.Name = "button16";
			this.button16.UseUnderline = true;
			this.button16.Label = global::Mono.Unix.Catalog.GetString ("Командная строка ( для опытных пользователей )");
			this.vpaned20.Add (this.button16);
			global::Gtk.Paned.PanedChild w8 = ((global::Gtk.Paned.PanedChild)(this.vpaned20 [this.button16]));
			w8.Resize = false;
			this.vpaned16.Add (this.vpaned20);
			this.vbox1.Add (this.vpaned16);
			global::Gtk.Box.BoxChild w10 = ((global::Gtk.Box.BoxChild)(this.vbox1 [this.vpaned16]));
			w10.Position = 2;
			this.Add (this.vbox1);
			if ((this.Child != null)) {
				this.Child.ShowAll ();
			}
			this.Show ();
			this.DeleteEvent += new global::Gtk.DeleteEventHandler (this.OnDeleteEvent);
			this.button14.Clicked += new global::System.EventHandler (this.OnButton14Clicked);
			this.button15.Clicked += new global::System.EventHandler (this.OnButton15Clicked);
			this.button16.Clicked += new global::System.EventHandler (this.OnButton16Clicked);
		}
	}
}
