using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


using System.IO;



namespace odtwarzacz_WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        List<Playlistelement> playlist;
        int tmpSelectedItem;
        
        public MainWindow()
        
        {
            InitializeComponent();
            playlist = new List<Playlistelement>();
            Slider_Volume.Value=(Slider_Volume.Maximum/100*50);
            tmpSelectedItem = -1;
        }


        #region Drop
        private void DropList_DragEnter(object sender, DragEventArgs e)
        {
            if (!e.Data.GetDataPresent(DataFormats.FileDrop) ||
                sender == e.Source)
            {
                e.Effects = DragDropEffects.None;
            }
        }
        private void Drop_On_ListView(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                // Note that you can have more than one file.
                string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);

                foreach (string plik in files)
                {
                    FileInfo FInfo = new FileInfo(plik);
                    // Sprawdza format
                    if ((FInfo.Extension != ".mp3") && (FInfo.Extension != ".avi"))
                    {
                        e.Effects = DragDropEffects.None;
                    }
                    else
                    {
                        e.Effects = DragDropEffects.All;
                        Playlistelement elem = new Playlistelement(FInfo.FullName, FInfo.Name);
                        ListView.Items.Add(elem.namedata);
                        playlist.Add(elem);
                    }
                }
                e.Handled = true;
            }
        }
        private void UIElement_OnPreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            this.DragMove();
        }
        #endregion
        #region Volume
        private void Slider_Volume_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            MediaElementWindow.Volume = Slider_Volume.Value;
            BitmapImage bi = new BitmapImage();
            if (Slider_Volume.Value > 0)
            {
                if (Slider_Volume.Value > (60* Slider_Volume.Maximum / 100))
                {
                    Volume_image.Source = global::odtwarzacz_WPF.Properties.Resources.vfull.ToImageSource();
                }
                else
                {
                    Volume_image.Source = global::odtwarzacz_WPF.Properties.Resources.vhalf.ToImageSource();
                }
            }
            else
            {
                Volume_image.Source = global::odtwarzacz_WPF.Properties.Resources.voff.ToImageSource();
            }
        }
        #endregion
        #region Buttons : play, next , forward ...

        void timer_tick(object sender, EventArgs e)
        {
            Slider_Timer.Value = MediaElementWindow.Position.TotalSeconds;
        }
        void Media_play(int index)
        {
            try
            {
                MediaElementWindow.Source = new Uri(playlist[index].sourcedata);
                System.Windows.Threading.DispatcherTimer dt = new System.Windows.Threading.DispatcherTimer();
                dt.Tick += new EventHandler(timer_tick);
                dt.Interval = new TimeSpan(0, 0, 1);
                dt.Start();
                MediaElementWindow.Play();
                labelAkcja.Content = "Odtwarzanie: " + playlist[index].namedata;
                tmpSelectedItem = index;
            }
            catch
            {
                new NullReferenceException("Blad sciezki pliku");
            }


        }
        private void Play_pause_Click(object sender, RoutedEventArgs e)
        {
            if (Button_Play_Pause.Content == FindResource("play_ico"))
            {
                // wcisnieta jest pauza
                if (MediaElementWindow.IsBuffering == true)
                {
                    MediaElementWindow.Play();
                    Button_Play_Pause.Content = FindResource("pause_ico");
                    labelAkcja.Content = "Wzwnowienie odtwarzania.";
                }
                //
                else if (ListView.SelectedItems.Count > 0)
                {
                    Media_play(ListView.SelectedIndex);
                    Button_Play_Pause.Content = FindResource("pause_ico");
                    labelAkcja.Content = "Wlaczenie zaznaczonego pliku .";
                }
                else if (ListView.Items.Count > 0)
                {
                    Media_play(0);
                    Button_Play_Pause.Content = FindResource("pause_ico");
                    labelAkcja.Content = "Odtworzenie pierwszej sciezki z listy.";
                }
                else
                    labelAkcja.Content = "W playliscie nie ma plikow do odtworzenia.";
            }
            else
            {
                Button_Play_Pause.Content = FindResource("play_ico");
                MediaElementWindow.Pause();
                labelAkcja.Content = "Pauza.";
            }
        }
        private void MouseDoubleClickOnPlaylist(object sender, MouseButtonEventArgs e)
        {
            Button_Play_Pause.Content = FindResource("pause_ico");
            Media_play(ListView.SelectedIndex);
            labelAkcja.Content = "Odtworzenie pliku po dwukrotnym kliknieciu na liste";
        }
        //cofnij o 10 sekund
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Threading.DispatcherTimer dt = new System.Windows.Threading.DispatcherTimer();
            dt.Tick += new EventHandler(timer_tick);

           // TimeSpan ts=  new TimeSpan(0,0,10);//dodaje godziny , minuty,sekundy)
            double seconds = 10;
            if (0 < (MediaElementWindow.Position.Seconds - seconds))
                dt.Interval = new TimeSpan(0, 0, Convert.ToInt16(MediaElementWindow.Position.Seconds - seconds));
            else
                dt.Interval = new TimeSpan(0, 0, 0);
            dt.Start();
            
        }
        //przewin w przod o 10 sekund
        private void Forward_Click(object sender, RoutedEventArgs e)
        {
 
            double seconds = 10;
            if (MediaElementWindow.Position.TotalSeconds > (MediaElementWindow.Position.Seconds + seconds))
            {
                MediaElementWindow.Pause();
                MediaElementWindow.Position = TimeSpan.FromSeconds(MediaElementWindow.Position.Seconds + seconds);
                MediaElementWindow.Play();
            }
            else
                Next_Click(sender, e);


        }
        //nastepny utwor
        private void Next_Click(object sender, RoutedEventArgs e)
        {
            if (tmpSelectedItem +2 < playlist.Count)
                Media_play(tmpSelectedItem + 1);
            else if (playlist.Count > 0)
                Media_play(0);
            else
                labelAkcja.Content = "Playlista jest pusta. Nie mozna odtworzyc nastepnego elementu.";
        }
        //poprzedni utwor
        private void Previous_Click(object sender, RoutedEventArgs e)
        {
            if ( 0 < tmpSelectedItem )
                Media_play( tmpSelectedItem - 1 );
            else if (playlist.Count > 0)
                Media_play(playlist.Count-1);
            else
                labelAkcja.Content = "Playlista jest pusta. Nie mozna odtworzyc poprzedniego elementu.";
        }
        #endregion


        private void exit_program(object sender, MouseButtonEventArgs e)
        {
            this.Close();
        }
        

        private void Update_Data_When_Media_player_opened(object sender, RoutedEventArgs e)
        {
            TimeSpan ts =TimeSpan.FromMilliseconds(MediaElementWindow.NaturalDuration.TimeSpan.TotalMilliseconds);
            Slider_Timer.Maximum = ts.TotalSeconds;
           
        }
        private void Slider_Timer_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            TimeSpan ts = TimeSpan.FromSeconds(e.NewValue);
            MediaElementWindow.Position = ts;
            if(MediaElementWindow.Position.TotalHours<1)
                LabelActuallyTime.Content = MediaElementWindow.Position.Minutes.ToString()+":"+MediaElementWindow.Position.Seconds.ToString();
            else
                LabelActuallyTime.Content = MediaElementWindow.Position.Hours.ToString()+":"+ MediaElementWindow.Position.Minutes.ToString() + ":" + MediaElementWindow.Position.Seconds.ToString();
        }

        private void wyjscie_Click(object sender, RoutedEventArgs e)
        {

        }



    }
}
