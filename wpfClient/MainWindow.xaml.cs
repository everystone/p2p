﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using p2p;
using System.Diagnostics;

namespace wpfClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private NetworkWrapper _net;
        public MainWindow()
        {
            InitializeComponent();

           

        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            _net = new NetworkWrapper(2222);
            _net.Connected += _net_Connected2;
        }

        private void _net_Connected2(string ip)
        {
            
        }

        private void _net_ProgressChanged(double progress)
        {
            MessageBox.Show("Progress: " + progress);
            Debug.WriteLine("Progress: " + progress);
        }
    }
}
