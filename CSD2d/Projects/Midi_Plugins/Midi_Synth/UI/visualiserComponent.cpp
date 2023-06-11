#include "visualiserComponent.h"
visualiserComponent::visualiserComponent(AudioPluginAudioProcessor* processor)
        : pAmp(processor)
{
    // starting timer for drawing
    startTimer(1);
    // loading background image
    background = ImageFileFormat::loadFrom(BinaryData::backgroundpanel_png, BinaryData::backgroundpanel_pngSize);

}

void visualiserComponent::paint(juce::Graphics& g) {
    // background
    g.drawImageAt(background, 0, 0);
    // creating a path for the pixels
    Path p;
    // max value
    float max = 0;

    if (pAmp != nullptr) {
        // retreiving Array values from buffer in the processor
        Array<float> history = pAmp->getHistory();

        for (int i = 0; i < history.size(); i++) {
            // drawing points based on position
            float x = getWidth() * static_cast<float>(i) / history.size();
            float y = (getHeight() / 2 - 20) + history[i] * ((getHeight() - 20) / 2);

            if (i == 0)
                p.startNewSubPath(x, y);
            else
                p.lineTo(x, y);
        }
        // making a range for amplitude
        max = FloatVectorOperations::findMaximum(history.getRawDataPointer(), history.size());
        max = jlimit<float>(0, 2, max);
    }
    // protection if there is no sound
    if (p.isEmpty())
        return;

    if (p.getBounds().getWidth() < 0.01)
        return;

    if (p.getBounds().getWidth() != p.getBounds().getWidth())
        return;
    g.setColour(Colours::deeppink);
    g.strokePath(p, PathStrokeType(1.0f + max / 2)); // Vary stroke width based on maximum value
    g.setColour(Colours::powderblue.withAlpha(0.7f));
    g.strokePath(p, PathStrokeType(0.5f + max / 2)); // Vary stroke width based on maximum value
    g.setColour(Colours::lightgreen.withAlpha(0.5f));
    g.strokePath(p, PathStrokeType(-0.4 + max / 2)); // Vary stroke width based on maximum value

}
void visualiserComponent::resized()
{
    // can be practical if there come more components
}

void visualiserComponent::timerCallback()
{
    repaint();
}