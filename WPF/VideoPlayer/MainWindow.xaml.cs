using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Demo.VideoPlayer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>

    public partial class MainWindow : Window
    {
        bool b = false;
        string _SelectedFilePath = null;

        class _FileInfo
        {
            public string FullName { get; set; }
            public string FileNameWithoutExtention
            {
                get
                {
                    return System.IO.Path.GetFileNameWithoutExtension(FullName);
                }
            }
            public override string ToString()
            {
                return FileNameWithoutExtention;
            }
        }

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Open_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Mediendateien(*.avi, *.mpg)|*.avi;*.mpg;*.wmv|Alle Dateien|*.*";
            dlg.Multiselect = true;
            if(dlg.ShowDialog().Value==true)
            {
                if(dlg.FileNames.Count()==0)
                    return;

                foreach(string filename in dlg.FileNames)
                {
                    _FileInfo NewFile = new _FileInfo { FullName = filename };
                    _fileList.Items.Add(NewFile);
                    b = false;
                    _SelectedFilePath = NewFile.FullName;
                    this.Title = NewFile.ToString();
                }
                Func();
                b = true;
            }
        }

        void mtl_CurrentTimeInvalidated(object sender, EventArgs e)
        {
            _positionProgress.Value = _media.Position.TotalSeconds;
        }
        private void PlayStop_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Style content = _playButton.Style;

            if (content == this.Resources["pauseBtnStyle"] as System.Windows.Style)
            {
                _media.Clock.Controller.Pause();
                _playButton.Style = this.Resources["playBtnStyle"] as System.Windows.Style;
            }
            if (content == this.Resources["playBtnStyle"] as System.Windows.Style && _fileList.HasItems)
            {
                _media.Clock.Controller.Resume();
                _playButton.Style = this.Resources["pauseBtnStyle"] as System.Windows.Style;
            }
        }

        private void Progress_MouseDown(object sender, MouseButtonEventArgs e)
        {
            double pos = _media.NaturalDuration.TimeSpan.TotalSeconds * e.GetPosition(_positionProgress).X / _positionProgress.RenderSize.Width;

            DoubleAnimation progressAnimation = new DoubleAnimation();
            progressAnimation.From = _media.Position.TotalSeconds;
            progressAnimation.To = pos;
            progressAnimation.FillBehavior = FillBehavior.Stop;
            progressAnimation.Duration = TimeSpan.FromMilliseconds(150);
            _positionProgress.BeginAnimation(ProgressBar.ValueProperty, progressAnimation);

            _media.Clock.Controller.Seek(TimeSpan.FromSeconds((int)pos), TimeSeekOrigin.BeginTime);
        }

        private void _mediaOpened(object sender, RoutedEventArgs e)
        {
            _positionProgress.Maximum = _media.NaturalDuration.TimeSpan.TotalSeconds;
            _playButton.Style = this.Resources["pauseBtnStyle"] as System.Windows.Style;
        }

        private void Window_Drop(object sender, DragEventArgs e)
        {
            string[] files = e.Data.GetData(DataFormats.FileDrop) as string[];
            if (files == null)
                return;

            foreach (string filename in files)
            {
                _FileInfo NewFile = new _FileInfo { FullName = filename };
                _fileList.Items.Add(NewFile);
                b = false;
                _SelectedFilePath = NewFile.FullName;
                this.Title = NewFile.ToString();
            }
            Func();
            b = true;
        }

        private void Slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (_media != null)
                _media.Volume = _Slider.Value * 0.1;
        }

        private void _fileList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (b)
            {
                _FileInfo NewFile = _fileList.SelectedValue as _FileInfo;
                _SelectedFilePath = NewFile.FullName;
                Func();
                this.Title = NewFile.ToString();
            }
        }

        private void StartClick(object sender, RoutedEventArgs e)
        {
            if (b)
                if (_positionProgress.Value < 5)
                    _media.Clock.Controller.Seek(TimeSpan.FromSeconds(0), TimeSeekOrigin.BeginTime);
                else
                    _media.Clock.Controller.Seek(TimeSpan.FromSeconds(_positionProgress.Value - 5), TimeSeekOrigin.BeginTime);
        }

        private void EndClick(object sender, RoutedEventArgs e)
        {
            if (b && _positionProgress.Value < _positionProgress.Maximum - 5)
                _media.Clock.Controller.Seek(TimeSpan.FromSeconds(_positionProgress.Value + 5), TimeSeekOrigin.BeginTime);
        }

        private void StopClick(object sender, RoutedEventArgs e)
        {
            if (b)
                _media.Clock.Controller.Stop();
        }

        public void Func()
        {
            MediaTimeline mtl = new MediaTimeline(new Uri(_SelectedFilePath));
            mtl.CurrentTimeInvalidated += mtl_CurrentTimeInvalidated;
            _media.Clock = mtl.CreateClock();
            _media.Clock.Controller.Resume();
        }
    }
}
