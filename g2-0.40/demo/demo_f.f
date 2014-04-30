        real demo_f
        real  a, b
        real d, d1, d2
        real color

        d=g2_open_vd()
        write (6,*) d        
        d1=g2_open_X11(100.0, 100.0)
        write (6,*) d1
        d2=g2_open_PS('demo_f.ps', 4.0, 1.0)
        write (6,*) d2

        call g2_attach(d, d1)
        call g2_attach(d, d2)

        call g2_plot(d, 50.0, 50.0)
        call g2_arc(d, 50.0, 50.0, 30.0, 20.0, 45.0, 180.0)

        color=g2_ink(d1, 1.0, 0.0, 0.0)
        call g2_pen(d1, color)
        write (6,*) color
        call g2_string(d1, 15.0, 75.0, 'TEST (Window)')

        color=g2_ink(d2, 0.0, 1.0, 0.0)
        call g2_pen(d2, color)
        write (6,*) color        
        call g2_string(d2, 15.0, 75.0, 'TEST (File)')

        call g2_pen(d, 1.0)
        call g2_circle(d, 20.0, 20.0, 10.0)
        call g2_string(d, 20.0, 20.0, 'All devices!')
        call g2_flush(d)

        call g2_close(d2)

        read (*,*) a

        stop
        end


