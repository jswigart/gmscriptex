#include "gmdebuggersettings.h"

GMDebuggerSettings::GMDebuggerSettings(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.comboStyles->addItem( "Windows", "windows" );
	ui.comboStyles->addItem( "WindowsXP", "windowsxp" );
	ui.comboStyles->addItem( "WindowsVista", "windowsvista" );
	ui.comboStyles->addItem( "Motif", "motif" );
	ui.comboStyles->addItem( "CDE", "cde" );
	ui.comboStyles->addItem( "Plastique", "plastique" );
	ui.comboStyles->addItem( "CleanLooks", "cleanlooks" );

	oldStyle = QApplication::style();
	QString oldStyleName = QApplication::style()->objectName();
	const int i = ui.comboStyles->findData( oldStyleName );
	ui.comboStyles->setCurrentIndex( i );

	ui.comboFonts->setCurrentFont( QApplication::font() );

	// slots
	connect(ui.comboStyles, SIGNAL(currentIndexChanged(int)), this, SLOT(StyleChanged()));
	connect(ui.comboFonts, 
		SIGNAL(currentFontChanged(const QFont &)), 
		this, 
		SLOT(FontChanged(const QFont &)));
}

GMDebuggerSettings::~GMDebuggerSettings()
{
}

void GMDebuggerSettings::StyleChanged()
{
	const int i = ui.comboStyles->currentIndex();
	QString styleName = ui.comboStyles->itemData( i ).toString();
	QApplication::setStyle( styleName );
}

void GMDebuggerSettings::FontChanged(const QFont & newFont)
{
	QApplication::setFont( newFont );

}