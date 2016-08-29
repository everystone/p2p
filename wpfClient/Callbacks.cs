using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using p2p;
using System.Windows;

namespace wpfClient
{
    class Net
    {
        private NetworkWrapper wrapper;
        public Net(short port)
        {
            this.wrapper = new NetworkWrapper(port);

            wrapper.ProgressChanged += Wrapper_ProgressChanged;
            
        }

        private void Wrapper_ProgressChanged(double progress)
        {
            MessageBox.Show("Progress Changed: " + progress);
        }

    }
}
